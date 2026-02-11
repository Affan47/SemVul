write(dimeOutput * const file)
{
  this->preWrite(file);

  file->writeGroupCode(10);
  file->writeDouble(this->center[0]);
  file->writeGroupCode(20);
  file->writeDouble(this->center[1]);
  file->writeGroupCode(30);
  file->writeDouble(this->center[2]);

  file->writeGroupCode(40);
  file->writeDouble(this->radius);

  file->writeGroupCode(50);
  file->writeDouble(this->startAngle);
  file->writeGroupCode(51);
  file->writeDouble(this->endAngle);

  return this->writeExtrusionData(file) && dimeEntity::write(file);
}
