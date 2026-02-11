CDMakeLabel(SymbolDesc,Layer,Label,X,Y,Xform,Pointer)

struct s *SymbolDesc;
int Layer;
char *Label;
int X,Y;
char Xform;
struct o **Pointer;
{
    struct la *LabelDesc;
    struct o *ObjectDesc;
    unsigned int size;

    if ((LabelDesc = alloc(la)) == NULL)
        return (CDError(CDMALLOCFAILED));
    if ((ObjectDesc = alloc(o)) == NULL)
        return (CDError(CDMALLOCFAILED));
    size = strlen(Label) + 2;
    if ((LabelDesc->laLabel = malloc(size)) == NULL)
        return (CDError(CDMALLOCFAILED));
    strcpy(LabelDesc->laLabel,Label);
    LabelDesc->laX = X;
    LabelDesc->laY = Y;
    LabelDesc->laXform = Xform;
    ObjectDesc->oRep = (struct o *)LabelDesc;
    ObjectDesc->oPrptyList = NULL;
    ObjectDesc->oInfo = 0;
    ObjectDesc->oType = CDLABEL;
    ObjectDesc->oLayer = Layer;


    ObjectDesc->oLeft   = X;
    ObjectDesc->oRight  = X + 400;
    ObjectDesc->oBottom = Y;
    ObjectDesc->oTop    = Y + 200;


    *Pointer = ObjectDesc;
    if (Not CDInsertObjectDesc(SymbolDesc,ObjectDesc))
        return (False);
    return (True);
}
