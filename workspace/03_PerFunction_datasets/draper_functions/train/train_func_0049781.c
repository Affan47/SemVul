MoveJump(float x, float y, float z, float horizontalSpeed, float max_height, uint32 id)
{
    Movement::MoveSplineInit init(*m_owner);
    init.MoveTo(x, y, z);
    init.SetParabolic(max_height, 0);
    init.SetVelocity(horizontalSpeed);
    init.Launch();
    Mutate(new EffectMovementGenerator(id));
}
