toCBuffer(OutBuffer *buf, HdrGenState *hgs)
{
    StorageClassDeclaration::stcToCBuffer(buf, storage_class);


    if (type)
        type->toCBuffer(buf, ident, hgs);
    else
        buf->writestring(ident->toChars());
    if (init)
    {   buf->writestring(" = ");
#if DMDV2
        ExpInitializer *ie = init->isExpInitializer();
        if (ie && (ie->exp->op == TOKconstruct || ie->exp->op == TOKblit))
            ((AssignExp *)ie->exp)->e2->toCBuffer(buf, hgs);
        else
#endif
            init->toCBuffer(buf, hgs);
    }
    buf->writeByte(';');
    buf->writenl();
}
