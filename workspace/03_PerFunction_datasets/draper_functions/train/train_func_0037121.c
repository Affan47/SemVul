OptimizeLoops()
{
    std::vector<NodeStatement*> optimized_body;
    for (std::vector<NodeStatement*>::iterator it= statements.begin(); it != statements.end(); ++it)
        if ((*it)->GetClassName() == STMT_LOOP)
        {
            StmtLoop* loop = (StmtLoop*)*it;
            loop->TakeOutVars(optimized_body);
            if (!loop->IsDummyLoop()) optimized_body.push_back(loop);
        }
        else if ((*it)->GetClassName() == STMT_IF)
        {
            StmtIf* if_stmt = (StmtIf*)*it;
            NodeStatement* new_stmt;
            if (!if_stmt->OptimizeIf(new_stmt)) optimized_body.push_back(*it);
            else
            {
                if (new_stmt != NULL) optimized_body.push_back(new_stmt);
                delete *it;
            }
        }
        else
        {
            optimized_body.push_back(*it);
        }
    statements.assign(optimized_body.begin(), optimized_body.end());
}
