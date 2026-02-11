KillPoint(ePoint*     p)
{
    tControlledPTR< ePoint > keep( p );
    RemovePoint(p);
    p->Unlink();
}
