addTemplateParams(DIE &Buffer, DIArray TParams) {

  for (unsigned i = 0, e = TParams.getNumElements(); i != e; ++i) {
    DIDescriptor Element = TParams.getElement(i);
    if (Element.isTemplateTypeParameter())
      Buffer.addChild(getOrCreateTemplateTypeParameterDIE(
                        DITemplateTypeParameter(Element)));
    else if (Element.isTemplateValueParameter())
      Buffer.addChild(getOrCreateTemplateValueParameterDIE(
                        DITemplateValueParameter(Element)));
  }

}
