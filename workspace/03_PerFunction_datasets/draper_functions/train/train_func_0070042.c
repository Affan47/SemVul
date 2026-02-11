Command_option(Command *cmd, struct params *p)
{
    bstring key = match_release(p, TKOPTION, 0);
    check(key, "Should have matched an option.");

    bstring value = NULL;
    int next = peek(p);

    if(next == TKOPTION || next == -1) {

        value = bfromcstr("");
    } else {

        value = match(p, next);
    }

    hash_alloc_insert(cmd->options, bdata(key), value);
    return;

error:
    cmd->error = 1;
    return;
}
