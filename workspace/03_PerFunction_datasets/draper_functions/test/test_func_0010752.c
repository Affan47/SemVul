ImportConstants(){
	const constants_t consts[]={
		{"AVInfo",10006},
		{"m1000",PRINT_MODE_M1000},
		{"m1024",PRINT_MODE_M1024},
		{"hex",PRINT_MODE_HEX},
		{"fcc",PRINT_MODE_FCC},
		{"ct",PRINT_MODE_COMPACT_TIME},
		{"sn",PRINT_MODE_SHORT_NAME},
		{"time",PRINT_MODE_TIME},
		{"cn", PRINT_MODE_CODEC_NAME},
		{"maxlist",77},
		{"sotona",0x29A},
		{"DIV3",FOURCC_DIV3},
		{"XVID",FOURCC_XVID},
		{"DIVX",FOURCC_DIVX},
		{"DX50",FOURCC_DX50}
	};
	int c;
	for (c=0;c<sizeof(consts)/sizeof(constants_t);c++)
		SetNumericVar(consts[c].name,consts[c].value);
}
