GetDistance(WorldObject* obj)
{
    float dx = GetX() - obj->GetX();
    float dy = GetY() - obj->GetY();
    float dz = GetZ() - obj->GetZ();
    float sizefactor = GetObjectSize() + obj->GetObjectSize();
    float dist = sqrt((dx*dx) + (dy*dy) + (dz*dz)) - sizefactor;
    return ( dist > 0 ? dist : 0);
}
