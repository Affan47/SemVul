M_Write(void)
{
  if(!MetaObject::M_Write())
    {
    METAIO_STREAM::cout << "MetaFEMObject: M_Write: Error parsing file" << METAIO_STREAM::endl;
    return false;
    }

  NodeListType::iterator it_Node = m_NodeList.begin();
  while(it_Node != m_NodeList.end())
    {
    FEMObjectNode* Node = *it_Node;
    this->M_Write_Node(Node);
    it_Node++;
    }
  *this->m_WriteStream << "\n<END>  % End of nodes\n\n";

  MaterialListType::iterator it_Material = m_MaterialList.begin();
  while(it_Material != m_MaterialList.end())
    {
    FEMObjectMaterial* Material = *it_Material;
    this->M_Write_Material(Material);
    it_Material++;
    }
  *this->m_WriteStream << "\n<END>  % End of material definition\n\n";


  ElementListType::iterator it_Element = m_ElementList.begin();
  while(it_Element != m_ElementList.end())
    {
    FEMObjectElement* Element = *it_Element;
    this->M_Write_Element(Element);
    it_Element++;
    }
  *this->m_WriteStream << "\n<END>  % End of element definition\n\n";

  LoadListType::iterator it_Load = m_LoadList.begin();
  while(it_Load != m_LoadList.end())
    {
    FEMObjectLoad* Load = *it_Load;
    this->M_Write_Load(Load);
    it_Load++;
    }
  *this->m_WriteStream << "\n<END>  % End of load definition\n\n";

  return true;
}
