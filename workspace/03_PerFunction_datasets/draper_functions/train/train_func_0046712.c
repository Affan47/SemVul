analyze_unsafe_length_jump(Classifier_Program &prog, Bitvector &active,
			   int jump)
{
    if (jump > 0)
	active[jump] = true;
    else if (prog.unsafe_length_output_everything == -1)
	prog.unsafe_length_output_everything = -jump;
    else if (prog.unsafe_length_output_everything != -jump)
	prog.unsafe_length_output_everything = -2;
}
