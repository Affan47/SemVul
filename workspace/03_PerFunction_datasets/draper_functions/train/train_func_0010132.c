tokenize( struct parser_req *req, char *line )
{
        struct line_token *curr;
        int bytes_forward = 0;
        int count = 0;
        int interested_cnt = 0;

        curr = req->tokens;

        curr = get_next_token( line, &bytes_forward, curr );
        if ( curr->token_len == 0 ) {
                DPRINT( "No tokens in line \n" );
                return NULL;
        }
        count++;

        do {
                TRACE( "Token %d \n", count );
                if ( count == req->interested_tokens[ interested_cnt ] ) {
                        TRACE( "Found interesting one \n" );

                        interested_cnt++;
                        if ( interested_cnt == req->interested_size ) {
                                TRACE( "Got all tokens \n" );

                                curr->next = NULL;
                                break;
                        } else {
                                curr->next = &(req->tokens[ interested_cnt ]);
                                curr = curr->next;
                        }
                }
                line = line + bytes_forward;
                curr = get_next_token( line, &bytes_forward, curr );
                count++;
        } while ( curr->token_len != 0 );

        if ( interested_cnt < req->interested_size ) {
                WARN( "There we not enough tokens!\n" );
                return NULL;
        }

        return req->tokens;
}
