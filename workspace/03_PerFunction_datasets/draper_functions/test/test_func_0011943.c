apply2(ast_sent* s)
    {
        if (s->get_nodetype()==AST_BFS)
        {
            in_bfs = false;
            current_bfs = NULL;
        }
        return true;
    }
