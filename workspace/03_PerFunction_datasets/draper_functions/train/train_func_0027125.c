report(const std::exception& exception, int depth) {
  std::cerr << std::string(depth * 2, ' ') << exception.what() << '\n';
  try {
    ::rethrow_if_nested(exception);
  } catch (const std::exception& exception) {
    report(exception, depth + 1);
  } catch (...) {
    return;
  }
}
