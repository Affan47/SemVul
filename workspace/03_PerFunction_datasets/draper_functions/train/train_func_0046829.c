operator<<(std::ostream& o, const CallFrame& fr)
{
    CallFrame::Registers r = fr._registers;

    for (size_t i = 0; i < r.size(); ++i) {
        if (i) o << ", ";
        o << i << ':' << '"' << r[i] << '"';
    }
    return o;

}
}
