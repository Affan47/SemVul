finish_array(int32 i)
{


  if (!glulx_mode) {

    if (array_base!=dynamic_array_area_size)
    {   if (dynamic_array_area_size-array_base==2)
        {   dynamic_array_area[array_base]   = i/256;
            dynamic_array_area[array_base+1] = i%256;
        }
        else
        {   if (i>=256)
                error("A 'string' array can have at most 256 entries");
            dynamic_array_area[array_base] = i;
        }
    }

  }
  else {
    if (array_base!=dynamic_array_area_size)
    {   if (dynamic_array_area_size-array_base==4)
        {
            dynamic_array_area[array_base]   = (i >> 24) & 0xFF;
            dynamic_array_area[array_base+1] = (i >> 16) & 0xFF;
            dynamic_array_area[array_base+2] = (i >> 8) & 0xFF;
            dynamic_array_area[array_base+3] = (i) & 0xFF;
        }
        else
        {   if (i>=256)
                error("A 'string' array can have at most 256 entries");
            dynamic_array_area[array_base] = i;
        }
    }

  }


  dynamic_array_area_size += i*array_entry_size;

}
