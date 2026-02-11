can_unmount (int p)
{
    int dx = parts[p].mount_dx;
    int dy = parts[p].mount_dy;
    if (!dx && !dy)
    {
        bool is_ext = false;
        for (int ep = 0; ep < external_parts.size(); ep++)
            if (external_parts[ep] == p)
            {
                is_ext = true;
                break;
            }
        if (external_parts.size() > 1 && is_ext)
            return false;
    }

    if (!part_flag (p, vpf_mount_point))
        return true;
    for (int i = 0; i < 4; i++)
    {
        int ndx = i < 2? (i == 0? -1 : 1) : 0;
        int ndy = i < 2? 0 : (i == 2? - 1: 1);
        if (!(dx + ndx) && !(dy + ndy))
            continue;
        if (parts_at_relative (dx + ndx, dy + ndy).size() > 0)
        {
            int cnt = 0;
            for (int j = 0; j < 4; j++)
            {
                int jdx = j < 2? (j == 0? -1 : 1) : 0;
                int jdy = j < 2? 0 : (j == 2? - 1: 1);
                std::vector<int> pc = parts_at_relative (dx + ndx + jdx, dy + ndy + jdy);
                if (pc.size() > 0 && part_with_feature (pc[0], vpf_mount_point) >= 0)
                    cnt++;
            }
            if (cnt < 2)
                return false;
        }
    }
    return true;
}
