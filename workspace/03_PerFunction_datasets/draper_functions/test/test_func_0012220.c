PrintMessage PARAMS((f, v, indent),
FILE* f _AND_
Message* v _AND_
unsigned short int indent)
{
    if (v == NULL)
        return;

    fprintf(f,"{ -- SEQUENCE --\n");

    Indent(f, indent + stdIndentG);
    fprintf(f,"version ");
    PrintMessageInt(f, (&v->version), indent + stdIndentG);
    fprintf(f, ",\n");
    Indent(f, indent + stdIndentG);
    fprintf(f,"community ");
    PrintAsnOcts(f, (&v->community), indent + stdIndentG);
    fprintf(f, ",\n");
    Indent(f, indent + stdIndentG);
    fprintf(f,"data ");
    PrintPDUs(f, (v->data), indent + stdIndentG);
    fprintf(f,"\n");
    Indent(f, indent);
    fprintf(f,"}\n");
}
