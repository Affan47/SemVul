update_selected_cubes()
{
   if( m_verbosity > 0 ) cout<<"[daisy] update_selected_cubes\n";

   for( int r=0; r<m_rad_q_no; r++ )
   {
      double seed_sigma = (r+1)*m_rad/m_rad_q_no/2.0;
      g_selected_cubes[r] = quantize_radius( seed_sigma );
      if( m_verbosity > 1 )
      {

         cout<<"[daisy] g_selected_cubes["<<r<<"] = "<<g_selected_cubes[r]<<" sigma: "<<m_cube_sigmas[ g_selected_cubes[r] ] <<endl;
      }
   }
}
