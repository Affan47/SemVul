toXML(bool verbose, int version) const
{

    if (version == 1) {

        if (_inconclusive)
            return "";

        tinyxml2::XMLPrinter printer(0, false, 1);
        printer.OpenElement("error", false);
        if (!_callStack.empty()) {
            printer.PushAttribute("file", _callStack.back().getfile().c_str());
            printer.PushAttribute("line", _callStack.back().line);
        }
        printer.PushAttribute("id", _id.c_str());
        printer.PushAttribute("severity", (_severity == Severity::error ? "error" : "style"));
        printer.PushAttribute("msg", (verbose ? _verboseMessage : _shortMessage).c_str());
        printer.CloseElement(false);
        return printer.CStr();
    }


    else if (version == 2) {
        tinyxml2::XMLPrinter printer(0, false, 2);
        printer.OpenElement("error", false);
        printer.PushAttribute("id", _id.c_str());
        printer.PushAttribute("severity", Severity::toString(_severity).c_str());
        printer.PushAttribute("msg", _shortMessage.c_str());
        printer.PushAttribute("verbose", fixInvalidChars(_verboseMessage).c_str());
        if (_inconclusive)
            printer.PushAttribute("inconclusive", "true");

        for (std::list<FileLocation>::const_reverse_iterator it = _callStack.rbegin(); it != _callStack.rend(); ++it) {
            printer.OpenElement("location", false);
            printer.PushAttribute("file", (*it).getfile().c_str());
            printer.PushAttribute("line", (*it).line);
            printer.CloseElement(false);
        }
        printer.CloseElement(false);
        return printer.CStr();
    }

    return "";
}
