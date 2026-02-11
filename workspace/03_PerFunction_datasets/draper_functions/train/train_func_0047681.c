suppressScaling (bool toggle)
  {
     makeThisCurrent();
     int status=0;
     if (toggle)
     {

        fits_set_bscale(m_parent->fptr(), 1.0, 0.0, &status);
     }
     else
     {


        fits_set_hdustruc(m_parent->fptr(), &status);
     }
  }
