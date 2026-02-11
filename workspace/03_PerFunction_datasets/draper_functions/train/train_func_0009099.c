create_tree_view()
{
  list_view=new Q3ListView(parent_widget);
  mapping=new Q3PtrDict<Kaptain>;
  parent_layout->addWidget(list_view);


  list_view->setSorting(-1);
  list_view->setRootIsDecorated(true);
  list_view->addColumn(QString());
  if (im->is(is_detailed))
    list_view->addColumn(QString());
  else
    list_view->header()->hide();


  widget_stack=new Q3WidgetStack(parent_widget);

  list<Intermediate *>::reverse_iterator ii;

  for (ii=im->children.rbegin();
       ii!=im->children.rend();
       ii++)
    if (*ii)
      {
        Kaptain * child=new Kaptain(*ii, this, parent_widget,
                                    parent_layout, parent_dialog);
        children.append(child);
      }
  select_defaults();

  if (stack_size)
    {

      widget_stack->addWidget(new QWidget(widget_stack),0);
      parent_layout->addWidget(widget_stack);
      connect(list_view, SIGNAL(currentChanged(Q3ListViewItem *)),
              SLOT(panel_selected(Q3ListViewItem *)));
    }
  else
    delete widget_stack;

  list_view->adjustSize();
}
