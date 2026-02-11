GenerateInitialFileLines()
{

    fprintf(f_names_enum_h,"/* Automatically generated, do not edit. */\n");
    fprintf(f_names_enum_h,"/* Generated on %s  %s */\n",__DATE__,__TIME__);
    fprintf(f_names_enum_h,"\n/* BEGIN FILE */\n\n");
    fprintf(f_names_enum_h,"#ifndef __DWARF_NAMES_ENUM_H__\n");
    fprintf(f_names_enum_h,"#define __DWARF_NAMES_ENUM_H__\n");


    fprintf(f_names_new_h,"/* Automatically generated, do not edit. */\n");
    fprintf(f_names_new_h,"/* Generated on %s  %s */\n",__DATE__,__TIME__);
    fprintf(f_names_new_h,"\n/* BEGIN FILE */\n\n");
    fprintf(f_names_new_h,"/* define DWARF_PRINT_PREFIX before this \n");
    fprintf(f_names_new_h,"   point if you wish to.  */\n");
    fprintf(f_names_new_h,"#ifndef DWARF_PRINT_PREFIX \n");
    fprintf(f_names_new_h,"#define DWARF_PRINT_PREFIX dwarf_\n");
    fprintf(f_names_new_h,"#endif\n");
    fprintf(f_names_new_h,"#define dw_glue(x,y) x##y\n");
    fprintf(f_names_new_h,"#define dw_glue2(x,y) dw_glue(x,y)\n");
    fprintf(f_names_new_h,"#define DWPREFIX(x) dw_glue2(DWARF_PRINT_PREFIX,x)\n");


    fprintf(f_names_h,"/* Generated routines, do not edit. */\n");
    fprintf(f_names_h,"/* Generated on %s  %s */\n",__DATE__,__TIME__);
    fprintf(f_names_h,"\n/* BEGIN FILE */\n\n");


    fprintf(f_names_c,"/* Generated routines, do not edit. */\n");
    fprintf(f_names_c,"/* Generated on %s  %s */\n",__DATE__,__TIME__);
    fprintf(f_names_c,"\n/* BEGIN FILE */\n\n");
    fprintf(f_names_c,"#include \"dwarf.h\"\n\n");
    fprintf(f_names_c,"#include \"libdwarf.h\"\n\n");

    if (use_tables) {
        fprintf(f_names_c,"typedef struct Names_Data {\n");
        fprintf(f_names_c,"    const char *l_name; \n");
        fprintf(f_names_c,"    unsigned    value;  \n");
        fprintf(f_names_c,"} Names_Data;\n\n");


        fprintf(f_names_c,"/* Use standard binary search to get entry */\n");
        fprintf(f_names_c,"static int\nfind_entry(Names_Data *table,"
            "const int last,unsigned value, const char **s_out)\n");
        fprintf(f_names_c,"{\n");
        fprintf(f_names_c,"    int low = 0;\n");
        fprintf(f_names_c,"    int high = last;\n");
        fprintf(f_names_c,"    int mid;\n");
        fprintf(f_names_c,"\n");
        fprintf(f_names_c,"    while (low < high) {\n");
        fprintf(f_names_c,"        mid = low + ((high - low) / 2);\n");
        fprintf(f_names_c,"        if (table[mid].value < value) {\n");
        fprintf(f_names_c,"            low = mid + 1;\n");
        fprintf(f_names_c,"        }\n");
        fprintf(f_names_c,"        else {\n");
        fprintf(f_names_c,"              high = mid;\n");
        fprintf(f_names_c,"        }\n");
        fprintf(f_names_c,"    }\n");
        fprintf(f_names_c,"\n");
        fprintf(f_names_c,"    if (low < last && table[low].value == value) {\n");
        fprintf(f_names_c,"        /* Found: low is the entry */\n");
        fprintf(f_names_c,"      *s_out = table[low].l_name;\n");
        fprintf(f_names_c,"      return DW_DLV_OK;\n");
        fprintf(f_names_c,"    }\n");
        fprintf(f_names_c,"    return DW_DLV_NO_ENTRY;\n");
        fprintf(f_names_c,"}\n");
        fprintf(f_names_c,"\n");
    }
}
