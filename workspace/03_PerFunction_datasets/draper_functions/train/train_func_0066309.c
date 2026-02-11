setValue(const SbMatrix & m)
{
  float scalerow = m[0][0] + m[1][1] + m[2][2];

  if (scalerow > 0.0f) {
    float s = static_cast<float>(sqrt(scalerow + m[3][3]));
    this->quat[3] = s * 0.5f;
    s = 0.5f / s;

    this->quat[0] = (m[1][2] - m[2][1]) * s;
    this->quat[1] = (m[2][0] - m[0][2]) * s;
    this->quat[2] = (m[0][1] - m[1][0]) * s;
  }
  else {
    int i = 0;
    if (m[1][1] > m[0][0]) i = 1;
    if (m[2][2] > m[i][i]) i = 2;

    int j = (i+1)%3;
    int k = (j+1)%3;

    float s = static_cast<float>(sqrt((m[i][i] - (m[j][j] + m[k][k])) + m[3][3]));

    this->quat[i] = s * 0.5f;
    s = 0.5f / s;

    this->quat[3] = (m[j][k] - m[k][j]) * s;
    this->quat[j] = (m[i][j] + m[j][i]) * s;
    this->quat[k] = (m[i][k] + m[k][i]) * s;
  }

  if (m[3][3] != 1.0f) this->operator*=(1.0f/static_cast<float>(sqrt(m[3][3])));
  return *this;
}
