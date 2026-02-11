gzdirect(gzFile file)
{
   gz_statep state;


   if (file == NULL)
      return 0;
   state = (gz_statep)file;


   if (state->mode == GZ_READ && state->how == LOOK && state->x.have == 0)
      (void)gz_look(state);


   return state->direct;
}
