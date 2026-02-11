read_cell_hex() {
  cell cell;
  std::cin >> std::hex >> cell >> std::dec;
  if (!std::cin.good())
    exit(1);
  return cell;
}
