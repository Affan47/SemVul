v_cg_init(const char *src_path)
{
	char	buf[1024];
	int	i;
	FILE	*f;

	VCGData.nodes[V_NT_OBJECT] = fopen("v_gen_pack_o_node.c", "w");
	VCGData.nodes[V_NT_GEOMETRY] = fopen("v_gen_pack_g_node.c", "w");
	VCGData.nodes[V_NT_MATERIAL] = fopen("v_gen_pack_m_node.c", "w");
	VCGData.nodes[V_NT_BITMAP] = fopen("v_gen_pack_b_node.c", "w");
	VCGData.nodes[V_NT_TEXT] = fopen("v_gen_pack_t_node.c", "w");
	VCGData.nodes[V_NT_CURVE] = fopen("v_gen_pack_c_node.c", "w");
	VCGData.nodes[V_NT_AUDIO] = fopen("v_gen_pack_a_node.c", "w");
	VCGData.nodes[V_NT_SYSTEM] = fopen("v_gen_pack_s_node.c", "w");
	VCGData.init = fopen("v_gen_pack_init.c", "w");
	VCGData.unpack = fopen("v_gen_unpack_func.h", "w");
	VCGData.verse_h = fopen("verse.h", "w");
	VCGData.internal_verse_h = fopen("v_internal_verse.h", "w");
	for(i = 0; i < V_NT_NUM_TYPES_NETPACK + 1; i++)
	{
		if(i == V_NT_NUM_TYPES_NETPACK)
			f = VCGData.init;
		else
			f = VCGData.nodes[i];
		fprintf(f,
			"/*\n"
			" * $Id$\n"
			" *\n"
			" * ***** BEGIN BSD LICENSE BLOCK *****\n"
			" *\n"
			" * Copyright (c) 2005-2008, The Uni-Verse Consortium.\n"
			" * All rights reserved.\n"
			" *\n"
			" * Redistribution and use in source and binary forms, with or without\n"
			" * modification, are permitted provided that the following conditions are\n"
			" * met:\n"
			" *\n"
			" *  * Redistributions of source code must retain the above copyright\n"
			" *    notice, this list of conditions and the following disclaimer.\n"
			" *  * Redistributions in binary form must reproduce the above copyright\n"
			" *    notice, this list of conditions and the following disclaimer in the\n"
			" *    documentation and/or other materials provided with the distribution.\n"
			" *\n"
			" * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS \"AS\n"
			" * IS\" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED\n"
			" * TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A\n"
			" * PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER\n"
			" * OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,\n"
			" * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,\n"
			" * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR\n"
			" * PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF\n"
			" * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING\n"
			" * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS\n"
			" * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.\n"
			" *\n"
			" * ***** END BSD LICENSE BLOCK *****\n"
			" *\n"
			" */\n\n"
			"/*\n"
			"** This is automatically generated source code -- do not edit.\n"
			"** Changes are affected either by editing the corresponding protocol\n"
			"** definition file (v_cmd_def_X.c where X=node type), or by editing\n"
			"** the code generator itself, in v_cmd_gen.c.\n"
			"*/\n\n");
		fprintf(f, "#include <stdlib.h>\n");
		fprintf(f, "#include <stdio.h>\n\n");
		fprintf(f, "#include \"v_cmd_gen.h\"\n");
		fprintf(f, "#if !defined(V_GENERATE_FUNC_MODE)\n");
		fprintf(f, "#include \"verse.h\"\n");
		fprintf(f, "#include \"v_cmd_buf.h\"\n");
		fprintf(f, "#include \"v_network_out_que.h\"\n");
		fprintf(f, "#include \"v_network.h\"\n");
		fprintf(f, "#include \"v_connection.h\"\n");
		fprintf(f, "#include \"v_util.h\"\n\n");
	}
	VCGData.cmd_id = 0;
	fprintf(f, "#include \"v_gen_unpack_func.h\"\n\n");
	fprintf(f,
		"#include \"verse.h\"\n\n\n"
		"extern void verse_send_packet_ack(uint32 packet_id);\n"
		"extern void verse_send_packet_nak(uint32 packet_id);\n\n");

	fprintf(VCGData.init, "void init_pack_and_unpack(void)\n{\n");
	fprintf(VCGData.verse_h,
		"/*\n"
		"** Verse API Header file (for use with libverse.a).\n"
		"** This is automatically generated code; do not edit.\n"
		"*/\n\n"
		"\n"
		"#if !defined VERSE_H\n"
		"\n"
		"#if defined __cplusplus\t\t/* Declare as C symbols for C++ users. */\n"
		"extern \"C\" {\n"
		"#endif\n\n"
		"#define\tVERSE_H\n\n");

	snprintf(buf, sizeof buf, "%sverse_header.h", src_path);
	f = fopen(buf, "r");
	if(f != NULL)
	{
		while((i = fgetc(f)) != EOF)
			fputc(i, VCGData.verse_h);
		fclose(f);
	}
	else
	{
		fprintf(stderr, "mkprot: Couldn't find \"%s\" input file\n", buf);
		return 0;
	}
	fprintf(VCGData.verse_h, "\n/* Command sending functions begin. ----------------------------------------- */\n\n");
	return 1;
}
