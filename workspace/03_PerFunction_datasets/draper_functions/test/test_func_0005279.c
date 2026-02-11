init_static_data( void )
{
   GLfloat f = 0.0F;
   GLint i = 0;
   for ( ; i < FOG_EXP_TABLE_SIZE ; i++, f += FOG_INCR) {
      exp_table[i] = EXPF(-f);
   }
   inited = 1;
}
