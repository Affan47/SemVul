Init(hashState *state, int hashbitlen)
{
	  state->databitlen = 0;
	  state->datasize_in_buffer = 0;


      state->hashbitlen = hashbitlen;


      switch (hashbitlen)
      {
            case 224: memcpy(state->x,JH224_H0,128); break;
            case 256: memcpy(state->x,JH256_H0,128); break;
            case 384: memcpy(state->x,JH384_H0,128); break;
            case 512: memcpy(state->x,JH512_H0,128); break;
      }

      return(SUCCESS);
}
