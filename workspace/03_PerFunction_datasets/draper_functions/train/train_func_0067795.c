parse_body_of_definition(void)
{   int commas_in_row;

    def_t_s = 0;

    do
    {   commas_in_row = -1;
        do
        {   get_next_token(); commas_in_row++;
        } while ((token_type == SEP_TT) && (token_value == COMMA_SEP));

        if (commas_in_row>1)
            error("Two commas ',' in a row in object/class definition");

        if ((token_type == EOF_TT)
            || ((token_type == SEP_TT) && (token_value == SEMICOLON_SEP)))
        {   if (commas_in_row > 0)
                error("Object/class definition finishes with ','");
            break;
        }

        if (token_type != SEGMENT_MARKER_TT)
        {   error_named("Expected 'with', 'has' or 'class' in \
object/class definition but found", token_text);
            break;
        }
        else
        switch(token_value)
        {   case WITH_SEGMENT:
                properties_segment(WITH_SEGMENT);
                break;
            case PRIVATE_SEGMENT:
                properties_segment(PRIVATE_SEGMENT);
                break;
            case HAS_SEGMENT:
                attributes_segment();
                break;
            case CLASS_SEGMENT:
                classes_segment();
                break;
        }

    } while (TRUE);

}
