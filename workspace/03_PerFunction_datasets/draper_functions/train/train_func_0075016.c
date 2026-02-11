do_generate_compile_shell(std::map<std::string,std::string>& setup)
{

    const char* gm_top = setup["GM_TOP"].c_str();
    const char* avro = setup["SUPPORT_AVRO"].c_str();

    fprintf(f_shell, "GM_TOP= %s\n",gm_top);
    fprintf(f_shell, "GM_GRAPH= ${GM_TOP}/apps/output_cpp/gm_graph\n",gm_top);
    fprintf(f_shell, "CC= g++\n");
    fprintf(f_shell, "CFLAGS = -g -O3 -fopenmp -I${GM_GRAPH}/inc -I. \n", gm_top);

    fprintf(f_shell, "LFLAGS = -L${GM_GRAPH}/lib -lgmgraph \n");
    if ((avro!= NULL) && (atoi(avro) != 0)) {

    }
    fprintf(f_shell, "include ${GM_TOP}/setup.mk\n");
    fprintf(f_shell, "include ${GM_TOP}/apps/output_cpp/common.mk\n");


    fprintf(f_shell, "\n");
    fprintf(f_shell, "%s : %s.cc %s.h\n", fname, fname, fname);
    fprintf(f_shell, "\t${CC} ${CFLAGS} $< ${LFLAGS} -o $@", fname, fname);
}
