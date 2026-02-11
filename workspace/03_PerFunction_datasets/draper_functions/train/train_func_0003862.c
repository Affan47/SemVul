approxEqual(const KEYPath &left, const KEYPath &right, const double eps)
{
  return left.m_elements.size() == right.m_elements.size()
         && std::equal(left.m_elements.begin(), left.m_elements.end(), right.m_elements.begin(),
                       boost::bind(&KEYPath::Element::approxEqualsTo, _1, _2, eps))
         ;
}
