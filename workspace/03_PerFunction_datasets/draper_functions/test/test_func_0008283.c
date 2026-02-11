CanPass(const eGameObject *gameObject,
                    const eHalfEdge   *edge)
{
    tASSERT(edge);
    tASSERT(gameObject);

    eWall* w = edge->GetWall();
    if (!w && edge->Other())
        w = edge->Other()->GetWall();

    return !gameObject->EdgeIsDangerous(w, gameObject->LastTime(), 0.5f);
}
