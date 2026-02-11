shorthand_newer(const nstring &filename)
{

    tree::pointer tp1 = tree_this::create();


    tree::pointer tp2 = tree_mtime::create(tp1);


    rpt_value::pointer vp3 = rpt_value_string::create(filename);
    tree::pointer tp3 = tree_constant::create(vp3);


    tree::pointer tp4 = tree_mtime::create(tp3);


    return tree_gt::create(tp2, tp4);
}
