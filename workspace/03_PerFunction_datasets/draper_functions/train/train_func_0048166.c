read_samples ( workout_t * w, unsigned char * buf )
{
  int            offset;
  int            lap_size;
  int            sample_size;
  unsigned long  accum;
  int            ok = 1;
  int            i;
  int            s;
  int            x;

  lap_size    = bytes_per_lap(w->type,w->mode,w->interval_mode);
  sample_size = bytes_per_sample(w->mode);
  offset      = header_size(w);

  if ( offset != 0 ) {


    offset += w->laps * lap_size;


    w->samples = (w->bytes - offset)/sample_size;


    ok = allocate_sample_space(w);


    if ( ok ) {


      for ( i = 0; i < w->samples; i++ ) {
	s = offset + i * sample_size;
	x = w->samples - 1 - i;
	w->hr_data[x] = buf[s];
	s++;

	if ( S710_HAS_ALTITUDE(w->mode) ) {
	  w->alt_data[x] = buf[s] + ((buf[s+1] & 0x1f)<<8) - 512;
	  if ( w->units.system == S710_UNITS_ENGLISH ) {
	    w->alt_data[x] *= 5;
	  }
	  s += 2;
	}

	if ( S710_HAS_SPEED(w->mode) ) {
	  if ( S710_HAS_ALTITUDE(w->mode) ) s -= 1;
	  w->speed_data[x] = ((buf[s] & 0xe0) << 3) + buf[s+1];
	  s += 2;
	  if ( S710_HAS_POWER(w->mode) ) {
	    w->power_data[x].power = buf[s] + (buf[s+1]<<8);
	    w->power_data[x].lr_balance = buf[s+2];
	    w->power_data[x].pedal_index = buf[s+3];
	    s += 4;
	  }
	  if ( S710_HAS_CADENCE(w->mode) ) w->cad_data[x] = buf[s];
	}
      }

      if ( S710_HAS_SPEED(w->mode) ) {
	accum = 0;
	for ( i = 0; i < w->samples; i++ ) {
	  w->dist_data[i] = accum / 57600.0;
	  accum += w->speed_data[i] * w->recording_interval;
	}
      }

    }
  } else {


    ok = 0;
  }

  return ok;
}
