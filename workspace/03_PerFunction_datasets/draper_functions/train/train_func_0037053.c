CDRemoveProperty(SymbolDesc,Pointer,Value)

struct s *SymbolDesc;
struct o *Pointer;
int Value;
{
    struct prpty *prptyDesc;
    struct prpty *prptyHead;
    struct prpty *prptyCopy;
    struct prpty *prptyTemp;

    if (Pointer == NULL)
        prptyHead = prptyDesc = SymbolDesc->sPrptyList;
    else
        prptyHead = prptyDesc = Pointer->oPrptyList;

    for (prptyCopy = NULL; prptyDesc != NULL;
        prptyCopy = prptyDesc,prptyDesc = prptyTemp) {
        prptyTemp = prptyDesc->prpty_Succ;

        if (prptyDesc->prpty_Value == Value) {
            if (prptyCopy == NULL)
                prptyHead = prptyDesc->prpty_Succ;
            else
                prptyCopy->prpty_Succ = prptyDesc->prpty_Succ;
            if (prptyDesc->prpty_String) free(prptyDesc->prpty_String);
            if (prptyDesc->prpty_Info) free(prptyDesc->prpty_Info);
            afree(prptyDesc,prpty);
            prptyDesc = prptyCopy;
        }
    }
    if (Pointer == NULL)
        SymbolDesc->sPrptyList = prptyHead;
    else
        Pointer->oPrptyList = prptyHead;
    return True;
}
