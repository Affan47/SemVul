try_convert_and_pair(
	struct schedule_state *s,
	struct schedule_instruction ** inst_list)
{
	struct schedule_instruction * list_ptr = *inst_list;
	while (list_ptr && *inst_list && (*inst_list)->NextReady) {
		int paired = 0;
		if (list_ptr->Instruction->U.P.Alpha.Opcode != RC_OPCODE_NOP
			&& list_ptr->Instruction->U.P.RGB.Opcode
						!= RC_OPCODE_REPL_ALPHA) {
				goto next;
		}
		if (list_ptr->NumWriteValues == 1
					&& convert_rgb_to_alpha(s, list_ptr)) {

			struct schedule_instruction * pair_ptr;
			remove_inst_from_list(inst_list, list_ptr);
			add_inst_to_list_score(&s->ReadyAlpha, list_ptr);

			for (pair_ptr = s->ReadyRGB; pair_ptr;
					pair_ptr = pair_ptr->NextReady) {
				if (merge_instructions(&pair_ptr->Instruction->U.P,
						&list_ptr->Instruction->U.P)) {
					remove_inst_from_list(&s->ReadyAlpha, list_ptr);
					remove_inst_from_list(&s->ReadyRGB, pair_ptr);
					pair_ptr->PairedInst = list_ptr;

					add_inst_to_list(&s->ReadyFullALU, pair_ptr);
					list_ptr = *inst_list;
					paired = 1;
					break;
				}

			}
		}
		if (!paired) {
next:
			list_ptr = list_ptr->NextReady;
		}
	}
}
