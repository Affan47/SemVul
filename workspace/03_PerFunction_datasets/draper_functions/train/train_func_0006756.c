AddToWorld()
{

    if (!IsInWorld())
        GetMap()->GetObjectsStore().insert<DynamicObject>(GetObjectGuid(), (DynamicObject*)this);

    Object::AddToWorld();
}
