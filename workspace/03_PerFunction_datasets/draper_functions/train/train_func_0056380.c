deflateEnd (z_streamp strm)
{
   struct internal_state_deflate *state;
   int status;

   if (strm == Z_NULL || strm->state == Z_NULL) return Z_STREAM_ERROR;
   state = (struct internal_state_deflate*)strm->state;

   status = state->status;
   if (status != INIT_STATE &&
         status != EXTRA_STATE &&
         status != NAME_STATE &&
         status != COMMENT_STATE &&
         status != HCRC_STATE &&
         status != BUSY_STATE &&
         status != FINISH_STATE) {
      return Z_STREAM_ERROR;
   }


   TRY_FREE(strm, state->pending_buf);
   TRY_FREE(strm, state->head);
   TRY_FREE(strm, state->prev);
   TRY_FREE(strm, state->window);

   ZFREE(strm, state);
   state = Z_NULL;

   return status == BUSY_STATE ? Z_DATA_ERROR : Z_OK;
}
