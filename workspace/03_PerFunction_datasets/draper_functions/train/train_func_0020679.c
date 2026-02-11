pair_instructions(struct schedule_state * s)
{
	struct schedule_instruction *rgb_ptr;
	struct schedule_instruction *alpha_ptr;


	rgb_ptr = s->ReadyRGB;
	while(rgb_ptr) {
		struct schedule_instruction * rgb_next = rgb_ptr->NextReady;
		alpha_ptr = s->ReadyAlpha;
		while(alpha_ptr) {
			struct schedule_instruction * alpha_next = alpha_ptr->NextReady;
			if (merge_instructions(&rgb_ptr->Instruction->U.P, &alpha_ptr->Instruction->U.P)) {


				remove_inst_from_list(&s->ReadyRGB, rgb_ptr);
				remove_inst_from_list(&s->ReadyAlpha, alpha_ptr);
				rgb_ptr->PairedInst = alpha_ptr;
				add_inst_to_list(&s->ReadyFullALU, rgb_ptr);
				break;
			}
			alpha_ptr = alpha_next;
		}
		rgb_ptr = rgb_next;
	}

	if (!s->Opt) {
		return;
	}


	try_convert_and_pair(s, &s->ReadyFullALU);


	try_convert_and_pair(s, &s->ReadyRGB);
}
