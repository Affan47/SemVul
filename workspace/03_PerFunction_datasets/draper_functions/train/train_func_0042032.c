_fill_buffer(osc *this)
{
  int i, phase_factor;
  event *e;
  sample *buf = this->buffer;
  sample *tbl = this->table;

  for( i = 0; i < TBASS_BUFF_SIZE;i++)
    {
      e = this->events[i];
      if(e){
	e->fire(e,(sample_producer*)this);

	this->events[i] = NULL;
      }
      phase_factor = this->phase_offset / this->freq;
      buf[i] = tbl[this->current_index + phase_factor];
      this->current_index += this->freq +
	(this->freq * this->freq_offset / MAX_FREQ_OFFSET);

      if(this->current_index + phase_factor >= RATE )
	{
	  this->current_index  = this->current_index + phase_factor - RATE;
	}

    }
}
