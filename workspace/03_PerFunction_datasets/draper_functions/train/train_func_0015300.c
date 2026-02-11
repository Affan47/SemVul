parser_scan_buffer(parser_context_t *ctx,char *buf,size_t buf_size)
{
   int i,type;
   u_char c;

   for(i=0;(i<buf_size) && (ctx->state != PARSER_STATE_DONE);i++)
   {
      ctx->consumed_len++;
      c = buf[i];


      type = parser_get_char_type(c);


      switch(ctx->state) {
         case PARSER_STATE_SKIP:
            if (type == PARSER_CHAR_NEWLINE)
               ctx->state = PARSER_STATE_DONE;


            break;

         case PARSER_STATE_BLANK:
            switch(type) {
               case PARSER_CHAR_BLANK:

                  break;

               case PARSER_CHAR_COMMENT:
                  ctx->state = PARSER_STATE_SKIP;
                  break;

               case PARSER_CHAR_NEWLINE:
                  ctx->state = PARSER_STATE_DONE;
                  break;

               case PARSER_CHAR_QUOTE:
                  ctx->state = PARSER_STATE_QUOTED_STRING;
                  break;

               default:

                  if (!tmp_token_add_char(ctx,c)) {
                     ctx->state = PARSER_STATE_STRING;
                  } else {
                     ctx->state = PARSER_STATE_SKIP;
                     ctx->error = PARSER_ERROR_NOMEM;
                  }
            }
            break;

         case PARSER_STATE_STRING:
            switch(type) {
               case PARSER_CHAR_BLANK:
                  if (!parser_move_tmp_token(ctx)) {
                     ctx->state = PARSER_STATE_BLANK;
                  } else {
                     ctx->state = PARSER_STATE_SKIP;
                     ctx->error = PARSER_ERROR_NOMEM;
                  }
                  break;

               case PARSER_CHAR_NEWLINE:
                  if (parser_move_tmp_token(ctx) == -1)
                     ctx->error = PARSER_ERROR_NOMEM;

                  ctx->state = PARSER_STATE_DONE;
                  break;

               case PARSER_CHAR_COMMENT:
                  if (parser_move_tmp_token(ctx) == -1)
                     ctx->error = PARSER_ERROR_NOMEM;

                  ctx->state = PARSER_STATE_SKIP;
                  break;

               case PARSER_CHAR_QUOTE:
                  ctx->error = PARSER_ERROR_UNEXP_QUOTE;
                  ctx->state = PARSER_STATE_SKIP;
                  break;

               default:

                  if (tmp_token_add_char(ctx,c) == -1) {
                     ctx->state = PARSER_STATE_SKIP;
                     ctx->error = PARSER_ERROR_NOMEM;
                  }
            }
            break;

         case PARSER_STATE_QUOTED_STRING:
            switch(type) {
               case PARSER_CHAR_NEWLINE:

                  ctx->error = PARSER_ERROR_UNEXP_EOL;
                  ctx->state = PARSER_STATE_DONE;
                  break;

               case PARSER_CHAR_QUOTE:
                  if (!parser_move_tmp_token(ctx)) {
                     ctx->state = PARSER_STATE_BLANK;
                  } else {
                     ctx->state = PARSER_STATE_SKIP;
                     ctx->error = PARSER_ERROR_NOMEM;
                  }
                  break;

               default:

                  if (tmp_token_add_char(ctx,c) == -1) {
                     ctx->state = PARSER_STATE_SKIP;
                     ctx->error = PARSER_ERROR_NOMEM;
                  }
            }
            break;
      }
   }

   return(ctx->state == PARSER_STATE_DONE);
}
