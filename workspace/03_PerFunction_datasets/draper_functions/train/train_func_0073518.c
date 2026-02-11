GetMyCharacterSceneNode(void)
{
    DrawObject *d = gui->domgr.Get(mychar->GetGUID());
    return d ? d->GetSceneNode() : NULL;
}
