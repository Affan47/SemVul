TriPlane(std::vector<FLOATVECTOR3>& posData, const FLOATVECTOR3 &normal, const float D) {
  std::vector<FLOATVECTOR3> newVertices;
  std::vector<FLOATVECTOR3> out;
  if (posData.size() % 3 != 0) return newVertices;

  for(auto iter = posData.begin(); iter < (posData.end()-2); iter += 3) {

    const FLOATVECTOR3 &a = (*iter);
    const FLOATVECTOR3 &b = (*(iter+1));
    const FLOATVECTOR3 &c = (*(iter+2));

    float fa = (normal ^ a) + D;
    float fb = (normal ^ b) + D;
    float fc = (normal ^ c) + D;
    if(fabs(fa) < (2 * std::numeric_limits<float>::epsilon())) { fa = 0; }
    if(fabs(fb) < (2 * std::numeric_limits<float>::epsilon())) { fb = 0; }
    if(fabs(fc) < (2 * std::numeric_limits<float>::epsilon())) { fc = 0; }
    if(fa >= 0 && fb >= 0 && fc >= 0) {

      continue;
    } else if(fa <= 0 && fb <= 0 && fc <= 0) {
      out.push_back(a);
      out.push_back(b);
      out.push_back(c);
    } else {
      std::vector<FLOATVECTOR3> tris, newVerts;
      SplitTriangle(a,b,c, fa,fb,fc,normal,D, tris, newVerts);


      out.insert(out.end(), tris.begin(), tris. end());
      newVertices.insert(newVertices.end(), newVerts.begin(), newVerts. end());
    }
  }

  posData = out;
  return newVertices;
}
