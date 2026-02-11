printLabelsBrief (std::ostream& os) const
{
  for (constLabelIterator l = m_labels.begin(); l != m_labels.end(); l++) {
    const Array2dFileLabel& label = **l;

    label.printBrief (os);
  }
}
