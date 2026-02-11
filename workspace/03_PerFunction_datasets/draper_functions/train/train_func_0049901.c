distance(const LatLng &p0, const LatLng &p1, const LatLng &p2)
{
  double out = 0.0;
  if (p1.lat() == p2.lat() && p1.lng() == p2.lng()) {
    out = hdist(p2, p0);
  }
  else {
    double dlat = (p2.lat()-p1.lat());
    double dlng = (p2.lng()-p1.lng());
    double u = ((p0.lat()-p1.lat())*dlat+(p0.lng()-p1.lng())*dlng)/(dlat*dlat + dlng*dlng);

    if (u <= 0) {
      out = hdist(p0, p1);
    }
    else if(u >= 1) {
      out = hdist(p0, p2);
    }
    else {
      out = hdist(p0, LatLng(p1.lat() + u*dlat, p1.lng() + u*dlng));
    }
  }
  return out;
}
