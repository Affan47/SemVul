allocate_poly(Layer,Path,BB,Pointer,Info)

int Layer;
struct p *Path;
struct ka *BB;
struct o **Pointer;
int Info;
{
    CDBogusPoly = True;
    if (Not CDMakePolygon(Parameters.kpCellDesc,
        Layer,Path,Pointer)) MallocFailed();
    CDBogusPoly = False;
    (*Pointer)->oInfo = Info;
    CDStatusInt = CDBB(Parameters.kpCellDesc,*Pointer,
        &BB->kaLeft,&BB->kaBottom,&BB->kaRight,&BB->kaTop);
}
