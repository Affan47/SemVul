getValue(SbVec3f & axis, float & radians) const
{
  if((this->quat[3] >= -1.0f) && (this->quat[3] <= 1.0f)) {
    radians = float(acos(this->quat[3])) * 2.0f;
    float scale = static_cast<float>(sin(radians / 2.0f));

    if(scale != 0.0f) {
      axis[0] = this->quat[0] / scale;
      axis[1] = this->quat[1] / scale;
      axis[2] = this->quat[2] / scale;


      return;
    }
  }


  axis.setValue(0.0f, 0.0f, 1.0f);
  radians = 0.0f;
}
