operator<<(std::ostream& o, const Button::MouseState& st)
{
    switch (st) {
        case Button::MOUSESTATE_UP: return o << "UP";
        case Button::MOUSESTATE_DOWN: return o << "DOWN";
        case Button::MOUSESTATE_OVER: return o << "OVER";
        case Button::MOUSESTATE_HIT: return o << "HIT";
        default: return o << "Unknown state";
    }
}
