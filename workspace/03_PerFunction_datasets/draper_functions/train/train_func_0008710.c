GetDebugContext() {
    never_unload_debugger_ = true;
    EnterDebugger debugger;
    return Debug::debug_context();
}
