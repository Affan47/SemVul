Align(const R2Vector& vector, RNBoolean normalized)
{

    this->vector = vector;
    if (!normalized) this->vector.Normalize();
    this->normal = R2Vector(this->vector.Y(), -this->vector.X());
}
