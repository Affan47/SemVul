load_texunit_sources( texenv_fragment_program *p, GLuint unit )
{
   const struct state_key *key = p->state;
   GLuint i;

   for (i = 0; i < key->unit[unit].NumArgsRGB; i++) {
      load_texenv_source( p, key->unit[unit].OptRGB[i].Source, unit );
   }

   for (i = 0; i < key->unit[unit].NumArgsA; i++) {
      load_texenv_source( p, key->unit[unit].OptA[i].Source, unit );
   }

   return GL_TRUE;
}
