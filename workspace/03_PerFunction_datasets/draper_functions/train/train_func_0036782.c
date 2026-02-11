displayList(list::node *ptr) const
{
    if(!ptr)
        std::cout << "nothing to display" << std::endl;
    while(ptr)
    {
        displayNode(ptr);
        ptr = ptr->next;
    }
}
