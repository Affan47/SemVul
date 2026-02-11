createAnonymousAARoot(StringRef Name, MDNode *Extra) {

  auto Dummy = MDNode::getTemporary(Context, None);

  SmallVector<Metadata *, 3> Args(1, Dummy.get());
  if (Extra)
    Args.push_back(Extra);
  if (!Name.empty())
    Args.push_back(createString(Name));
  MDNode *Root = MDNode::get(Context, Args);


  Root->replaceOperandWith(0, Root);


  return Root;
}
