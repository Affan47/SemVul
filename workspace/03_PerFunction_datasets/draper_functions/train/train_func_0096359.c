SetNodePosition(uint32 id, uint32 point, float x, float y, float z)
{
    WorldDatabase.PExecuteLog("UPDATE creature_movement SET position_x=%f, position_y=%f, position_z=%f WHERE id=%u AND point=%u", x, y, z, id, point);
    WaypointPathMap::iterator itr = m_pathMap.find(id);
    if (itr == m_pathMap.end())
        { return; }

    WaypointPath::iterator find = itr->second.find(point);
    if (find != itr->second.end())
    {
        find->second.x = x;
        find->second.y = y;
        find->second.z = z;
    }
}
