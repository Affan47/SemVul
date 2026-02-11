InitializeForInput(const InputType& input)
{
  ClearCache();
  if(ConfusionNet const* cn = dynamic_cast<ConfusionNet const*>(&input)) {
    Cache(*cn);
  } else if(Sentence const* s = dynamic_cast<Sentence const*>(&input)) {

    DisableCache();
  }
  if (!m_Table.get()) {

    m_Table.reset(new PrefixTreeMap());
    m_Table->Read(m_FilePath+".binlexr");
  }
}
