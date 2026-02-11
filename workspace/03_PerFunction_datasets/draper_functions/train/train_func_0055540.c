sixtp_handle_catastrophe(sixtp_sax_data *sax_data)
{


    GSList *lp;
    GSList **stack = &(sax_data->stack);

    g_critical("parse failed at:");
    sixtp_print_frame_stack(sax_data->stack, stderr);

    while (*stack)
    {
        sixtp_stack_frame *current_frame = (sixtp_stack_frame *) (*stack)->data;


        if (current_frame->parser->fail_handler)
        {
            GSList *sibling_data;
            gpointer parent_data;

            if ((*stack)->next == NULL)
            {

                parent_data = NULL;
                sibling_data = NULL;
            }
            else
            {
                sixtp_stack_frame *parent_frame =
                    (sixtp_stack_frame *) (*stack)->next->data;
                parent_data = parent_frame->data_for_children;
                sibling_data = parent_frame->data_from_children;
            }

            current_frame->parser->fail_handler(current_frame->data_for_children,
                                                current_frame->data_from_children,
                                                sibling_data,
                                                parent_data,
                                                sax_data->global_data,
                                                &current_frame->frame_data,
                                                current_frame->tag);
        }


        for (lp = current_frame->data_from_children; lp; lp = lp->next)
        {
            sixtp_child_result *cresult = (sixtp_child_result *) lp->data;
            if (cresult->fail_handler)
            {
                cresult->fail_handler(cresult);
            }
        }

        if ((*stack)->next == NULL)
        {


            break;
        }

        *stack = sixtp_pop_and_destroy_frame(*stack);
    }
}
