op1000(UINT16 opcode)
{
	switch ((opcode >> 8) & 15)
	{
	case  0: MOVBS4(opcode & 0x0f, Rm); 	break;
	case  1: MOVWS4(opcode & 0x0f, Rm); 	break;
	case  2: NOP(); 						break;
	case  3: NOP(); 						break;
	case  4: MOVBL4(Rm, opcode & 0x0f); 	break;
	case  5: MOVWL4(Rm, opcode & 0x0f); 	break;
	case  6: NOP(); 						break;
	case  7: NOP(); 						break;
	case  8: CMPIM(opcode & 0xff);			break;
	case  9: BT(opcode & 0xff); 			break;
	case 10: NOP(); 						break;
	case 11: BF(opcode & 0xff); 			break;
	case 12: NOP(); 						break;
	case 13: BTS(opcode & 0xff);			break;
	case 14: NOP(); 						break;
	case 15: BFS(opcode & 0xff);			break;
	}
}
