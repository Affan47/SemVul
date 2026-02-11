endSlide()
{
  m_outputSink << "</svg:svg>\n";
  m_vec.append(m_outputSink.str().c_str());
  m_outputSink.str("");
}
