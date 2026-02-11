ParserPop(Parser p)
{
    InputSource source;

    source = p->source;
    Fclose(source->file16);
    p->source = source->parent;

    if(source->entity->type == ET_external)
	Free(source->line);
    Free(source);
}
