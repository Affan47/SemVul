KillEdge (eHalfEdge*  e)
{
    tControlledPTR< eHalfEdge > keep( e );
    RemoveEdge(e);
    tControlledPTR< eHalfEdge > o ( e->other );

    e->Unlink();

    if (o)
    {
        KillEdge(o);
    }
}
