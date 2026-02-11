intern_data_parent_part_one(DDS & dds,
                                      ConstraintEvaluator & eval,
                                      sequence_values_stack_t &
                                      sequence_values_stack)
{
    DBG(cerr << "Entering intern_data_parent_part_one for " << name() << endl);

    int i = (get_starting_row_number() != -1) ? get_starting_row_number() : 0;


    bool status = read_row(i, dds, eval, false);


    SequenceValues::size_type orig_stack_size = sequence_values_stack.size() ;

    while (status
           && (get_ending_row_number() == -1
               || i <= get_ending_row_number()))
    {
        i += get_row_stride();
        for (Vars_iter iter = var_begin(); iter != var_end(); iter++) {
            if ((*iter)->send_p()) {
                switch ((*iter)->type()) {
                case dods_sequence_c:
                	static_cast<Sequence&>(**iter).intern_data_private(
                            eval, dds, sequence_values_stack);
                    break;

                default:
                    (*iter)->intern_data(eval, dds);
                    break;
                }
            }
        }

        set_read_p(false);

        status = read_row(i, dds, eval, false);
    }


    reset_row_number();


    if( sequence_values_stack.size() > orig_stack_size )
    {
	DBG2(cerr << "    popping d_values (" << sequence_values_stack.top()
	     << ") off stack; size: " << sequence_values_stack.size() << endl);
	sequence_values_stack.pop();
    }
    DBG(cerr << "Leaving intern_data_parent_part_one for " << name() << endl);
}
