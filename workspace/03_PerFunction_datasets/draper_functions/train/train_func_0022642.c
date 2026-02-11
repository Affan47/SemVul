process_children(clish_shell_t *shell,
                 TiXmlElement  *element,
                 void          *parent=NULL)
{
    for(TiXmlNode *node = element->FirstChild();
        NULL           != node;
        node            = element->IterateChildren(node))
    {

        process_node(shell,node,parent);
    }
}
